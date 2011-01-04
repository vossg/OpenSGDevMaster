// -*- Mode:C++ -*-

#include <OSGFieldContainerUtils.h>
#include <OSGGLUT.h>
#include <OSGGLUTWindow.h>
#include <OSGGroup.h>
#include <OSGManipulatorManager.h>
#include <OSGNameAttachment.h>
#include <OSGNode.h>
#include <OSGSimpleGeometry.h>
#include <OSGSimpleSceneManager.h>
#include <OSGTransform.h>
#include <OSGTypedGeoIntegralProperty.h>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <cstdlib>
#include <iostream>

namespace
{
    std::ostream&
    operator<<(std::ostream& os, OSG::Pnt3f const& p)
    {
        os.width(9);

        return os << std::fixed << std::setprecision(4)
                  << std::right << std::setfill(' ') << std::setw(8) << p[0] << ' '
                  << std::right << std::setfill(' ') << std::setw(8) << p[1] << ' '
                  << std::right << std::setfill(' ') << std::setw(8) << p[2];
    }

    std::ostream&
    operator<<(std::ostream& os, OSG::Vec3f const& v)
    {
        os.width(9);

        return os << std::fixed << std::setprecision(4)
                  << std::right << std::setfill(' ') << std::setw(8) << v[0] << ' '
                  << std::right << std::setfill(' ') << std::setw(8) << v[1] << ' '
                  << std::right << std::setfill(' ') << std::setw(8) << v[2];
    }

    std::ostream&
    operator<<(std::ostream& os, OSG::Vec4f const& v)
    {
        os.width(9);

        return os << std::fixed << std::setprecision(4)
                  << std::right << std::setfill(' ') << std::setw(8) << v[0] << ' '
                  << std::right << std::setfill(' ') << std::setw(8) << v[1] << ' '
                  << std::right << std::setfill(' ') << std::setw(8) << v[2] << ' '
                  << std::right << std::setfill(' ') << std::setw(8) << v[3];
    }

    namespace matrix
    {
        class wrap : private boost::noncopyable
        {
          public:

            wrap(OSG::Node* a)
                : boost::noncopyable(),
                  xform_()
            {
                assert(0 != a);

                xform_ = a->getCore<OSG::Transform>();

                assert(0 != xform_);
            }

            wrap(OSG::Transform* a)
                : boost::noncopyable(),
                  xform_(a)
            {
                assert(0 != xform_);
            }

            OSG::Matrix const& get() const
            {
                return xform_->getMatrix();
            }

            OSG::Matrix set(OSG::Matrix const& a)
            {
                OSG::Matrix result(get());

                xform_->setMatrix(a);

                return result;
            }

            OSG::Matrix& edit() const
            {
                return xform_->editMatrix();
            }

          private:

            OSG::Transform* xform_;

        };

        class decompose
        {
          public:
            OSG::Vec3f      translation;
            OSG::Quaternion rotation;
            OSG::Vec3f      scale_factor;
            OSG::Quaternion scale_orientation;

            decompose(OSG::Matrix const& a)
                : translation(),
                  rotation(),
                  scale_factor(),
                  scale_orientation()
            {
                a.getTransform(translation, rotation, scale_factor, scale_orientation);
            }
        };

        OSG::Matrix
        inverse(OSG::Matrix const& a)
        {
            OSG::Matrix result(a);

            assert(false != result.invert());

            return result;
        }

        OSG::Matrix
        transpose(OSG::Matrix const& a)
        {
            OSG::Matrix result(a);

            assert(false != result.transpose());

            return result;
        }

        void
        print(OSG::SceneGraphPrinter* sgp, OSG::NodeCore* core)
        {
            OSG::Transform* const xform(dynamic_cast<OSG::Transform*>(core));

            if (0 != xform)
            {
                OSG::Matrix const& m(xform->getMatrix());

                if (OSG::Matrix::identity() == m)
                {
                    sgp->indentStream() << "identity\n";
                }
                else
                {
                    sgp->indentStream() << '\n' << m;
                }
            }
            else
            {
                sgp->indentStream() << "invalid node core @" << core << ", not OSG::Transform-based\n";
            }
        }

    } // namespace matrix {

    void
    dump_scene(OSG::Node* n, std::ostream& os = std::cout)
    {
        if (0 != n)
        {
            OSG::SceneGraphPrinter sgp(n);

            sgp.addPrintFunc(OSG::Transform::getClassType(),          &matrix::print);
            // don't want to see OSG::Manipulator coordinate axis be default
            // sgp.addPrintFunc(OSG::ComponentTransform::getClassType(), &matrix::print);
            sgp.addPrintFunc(OSG::MoveManipulator::getClassType(),    &matrix::print);
            sgp.addPrintFunc(OSG::RotateManipulator::getClassType(),  &matrix::print);
            sgp.addPrintFunc(OSG::ScaleManipulator::getClassType(),   &matrix::print);

            sgp.printDownTree(os);
        }
    }

    void
    dump_xform(std::string const& n, OSG::Matrix const& m, OSG::Matrix const& w)
    {
        static unsigned const tabsize(8);

        unsigned i(1);

        while (n.length() > (i * tabsize))
            ++i;

        i = std::max(static_cast<unsigned>(2), i);

        std::string const prefix1(i - 1, '\t');
        std::string const prefix2(i + 1, '\t');

        OSG::Matrix const mt(matrix::transpose(m));
        OSG::Matrix const wt(matrix::transpose(w));

        std::cout << n
                  << prefix1 << mt[0] << "\t\t" << wt[0] << '\n'
                  << prefix2 << mt[1] << "\t\t" << wt[1] << '\n'
                  << prefix2 << mt[2] << "\t\t" << wt[2] << '\n'
                  << prefix2 << mt[3] << "\t\t" << wt[3] << '\n'
                  << std::endl;
    }

    struct object_type
    {
      public:
        OSG::NodeRefPtr rootN;
        OSG::NodeRefPtr xformTranslationN;
        OSG::NodeRefPtr pivotN;
        OSG::NodeRefPtr pivotGeoN;
        OSG::NodeRefPtr xformScaleN;
        OSG::NodeRefPtr xformRotationN;
        OSG::NodeRefPtr pivotInvN;
        OSG::NodeRefPtr intersectN;
        OSG::NodeRefPtr manipulatorRootN;
        OSG::NodeRefPtr manipulatorN;
        OSG::NodeRefPtr modelN;

        object_type(OSG::NodeRefPtr a, OSG::NodeRefPtr b = 0)
            : rootN               (OSG::Node::create()),
              xformTranslationN   (OSG::Node::create()),
              pivotN              (OSG::Node::create()),
              pivotGeoN           (OSG::makeSphere(2, 0.03)),
              xformScaleN         (OSG::Node::create()),
              xformRotationN      (OSG::Node::create()),
              pivotInvN           (OSG::Node::create()),
              intersectN          (OSG::Node::create()),
              manipulatorRootN    (OSG::Node::create()),
              manipulatorN        (a),
              modelN              (OSG::Node::create()),
              use_changed_functor_(false)
        {
            assert((0 != manipulatorN) && (0 != manipulatorN->getCore()));

            {
                rootN->            setCore(OSG::Group::create());
                pivotN->           setCore(OSG::Transform::create());
                // pivotGeoN already set
                xformScaleN->      setCore(OSG::Transform::create());
                xformRotationN->   setCore(OSG::Transform::create());
                pivotInvN->        setCore(OSG::Transform::create());
                xformTranslationN->setCore(OSG::Transform::create());
                intersectN->       setCore(OSG::Group::create());
                manipulatorRootN-> setCore(OSG::Transform::create());
                // manipulatorN already set
                modelN->           setCore(OSG::Transform::create());
            }

            // modelN
            if (0 != b)
            {
                modelN->addChild(b);
            }
            else
            {
                OSG::NodeRefPtr tmp(OSG::makeBox(1, 0.25, 0.5, 1, 1, 1));

                OSG::setName(tmp, "obj-model-box");

                modelN->addChild(tmp);
            }

            // manipulatorRootN -> [manipulatorN]
            // nothing to do

            // intersectN -> (modelN, manipulatorRootN)
            intersectN->addChild(modelN);
            intersectN->addChild(manipulatorRootN);

            // xformTranslationN -> intersectN
            xformTranslationN->addChild(intersectN);

            // pivotInvN -> xformTranslationN
            pivotInvN->addChild(xformTranslationN);

            // xformRotationN -> pivotInvN
            xformRotationN->addChild(pivotInvN);

            // xformScaleN -> xformRotationN
            xformScaleN->addChild(xformRotationN);

            // pivotGeoN
            // nothing to do

            // pivotN -> ([pivotGeoN], xformScaleN)
            pivotN->addChild(xformScaleN);

            // rootN -> pivotN
            rootN->addChild(pivotN);

            {
                OSG::setName(rootN,             "obj-root");
                OSG::setName(xformTranslationN, "obj-xform-trans");
                OSG::setName(pivotN,            "obj-pivot");
                OSG::setName(pivotGeoN,         "obj-pivot-geo");
                OSG::setName(xformScaleN,       "obj-xform-scale");
                OSG::setName(xformRotationN,    "obj-xform-rot");
                OSG::setName(pivotInvN,         "obj-pivot-inverse");
                OSG::setName(manipulatorN,      "obj-manipulator");
                OSG::setName(intersectN,        "obj-intersect");
                OSG::setName(manipulatorRootN,  "obj-manipulator-root");
                OSG::setName(manipulatorN,      "obj-manipulator");
                OSG::setName(modelN,            "obj-model");
            }
        }

        ~object_type()
        {
            modelN            = 0;
            manipulatorN      = 0;
            manipulatorRootN  = 0;
            intersectN        = 0;
            xformTranslationN = 0;
            pivotInvN         = 0;
            xformRotationN    = 0;
            xformScaleN       = 0;
            pivotGeoN         = 0;
            pivotN            = 0;

            // only the following is strictly necessary
            rootN             = 0;
        }

        void toggle_change_functors()
        {
            if (!use_changed_functor_) {
                xformTranslationN->getCore()->
                    addChangedFunctor(boost::bind(&object_type::changed_cb, this, xformTranslationN, _1, _2),
                                      "xform_translation_changed_cb");
                xformRotationN->getCore()->
                    addChangedFunctor(boost::bind(&object_type::changed_cb, this, xformRotationN,    _1, _2),
                                      "xform_rotation_changed_cb");
                xformScaleN->getCore()->
                    addChangedFunctor(boost::bind(&object_type::changed_cb, this, xformScaleN,       _1, _2),
                                      "xform_scale_changed_cb");
            } else {
                xformTranslationN->getCore()->clearChangedFunctors();
                xformRotationN->   getCore()->clearChangedFunctors();
                xformScaleN->      getCore()->clearChangedFunctors();
            }

            use_changed_functor_ = !use_changed_functor_;
        }

        void dump_xforms()
        {
            if (0 !=  pivotN) {
                dump_xform("           pivot:",
                           matrix::wrap(pivotN).get(), pivotN->getToWorld());
            }

            if ((0 !=  xformScaleN) && (0 !=  xformRotationN)) {
                OSG::Matrix m(matrix::wrap(xformScaleN).get());

                m.mult(matrix::wrap(xformRotationN).get());

                dump_xform("scale + rotation:",
                           m, xformRotationN->getToWorld());
            }

            if (0 !=  pivotInvN) {
                dump_xform("       pivot-inv:",
                           matrix::wrap(pivotInvN).get(), pivotInvN->getToWorld());
            }

            if (0 !=  xformTranslationN) {
                dump_xform("     translation:",
                           matrix::wrap(xformTranslationN).get(), xformTranslationN->getToWorld());
            }

            if (0 !=  manipulatorRootN) {
                dump_xform("manipulator-root:",
                           matrix::wrap(manipulatorRootN).get(), manipulatorRootN->getToWorld());
            }

            if (0 !=  manipulatorN) {
                dump_xform("     manipulator:",
                           matrix::wrap(manipulatorN).get(), manipulatorN->getToWorld());
            }

            if (0 !=  modelN) {
                dump_xform("           model:",
                           matrix::wrap(modelN).get(), modelN->getToWorld());
            }
        }

      private:

        bool use_changed_functor_;

        void
        changed_cb(OSG::NodeRefPtr a, OSG::FieldContainer* fc, OSG::BitVector fm)
        {
            std::cout << "object_type::changed_cb(" << OSG::getName(a) << ")" << std::endl;

            OSG::Transform* xform(dynamic_cast<OSG::Transform*>(fc));

            if (0 != xform)
            {
                if (0 != (fm & OSG::Transform::MatrixFieldMask))
                {
                    dump_xforms();
                }
            }
        }

    };

    OSG::GLUTWindowUnrecPtr  window(0);
    OSG::ManipulatorManager* manipulatorMgr(0);
    OSG::SimpleSceneManager* sceneMgr(0);

    OSG::NodeRefPtr          sceneRootN(0);
    object_type*             object(0);

    bool                     selected(false);
    bool                     uniform_scale(true);

    OSG::Node*
    find_path(OSG::Node* const from, OSG::Node* const to)
    {
        OSG::Node* result(from);

        while (0 != result)
        {
            if (to == result)
                break;

            result = result->getParent();
        }

        return result;
    }

    void
    set_pivot(OSG::Pnt3f const& point, OSG::Vec3f const& normal)
    {
        if (selected)
        {
            std::cout << "set_pivot: [" << point << "][" << normal << ']' << std::endl;

            OSG::Matrix new_pivot;

            { // p_n = w^-1 * [x,y,z]^T
                new_pivot.setTranslate(point);

                OSG::Matrix const parent_absolute(object->pivotN->getParent()->getToWorld());

                new_pivot.multLeft(matrix::inverse(parent_absolute));
            }

            // p_n^-1
            OSG::Matrix new_pivot_inv(matrix::inverse(new_pivot));

            OSG::Matrix new_trans(matrix::wrap(object->xformTranslationN).get());

            { // t_n = p_n * r_n^-1 * s_n^-1 * p_n^-1 * p_o * s_o * r_o * p_o^-1 * t_o
                OSG::Matrix const rot  (matrix::wrap(object->xformRotationN).get());
                OSG::Matrix const scale(matrix::wrap(object->xformScaleN).get());

                new_trans.multLeft(matrix::wrap(object->pivotInvN).get());
                new_trans.multLeft(rot);
                new_trans.multLeft(scale);
                new_trans.multLeft(matrix::wrap(object->pivotN).get());
                new_trans.multLeft(new_pivot_inv);
                new_trans.multLeft(matrix::inverse(scale));
                new_trans.multLeft(matrix::inverse(rot));
                new_trans.multLeft(new_pivot);
            }

            OSG::Matrix new_manip_root(new_pivot);

            { // mr_n = t_n^-1 * p_n [* manipulator^-1]
                new_manip_root.multLeft(matrix::inverse(new_trans));
                // new_manip_root.mult(matrix::inverse(matrix::wrap(object->manipulatorN).get()));
            }

            { // apply
                matrix::wrap(object->pivotN)           .set(new_pivot);
                matrix::wrap(object->pivotInvN)        .set(new_pivot_inv);
                matrix::wrap(object->xformTranslationN).set(new_trans);
                matrix::wrap(object->manipulatorRootN) .set(new_manip_root);
            }
        }
    }

    void
    deselect()
    {
        if (selected)
        {
            object->manipulatorRootN->subChild(object->manipulatorN);
            object->pivotN->          subChild(object->pivotGeoN);

            sceneMgr->setHighlight(0);

            selected = false;
        }
    }

    void
    select()
    {
        deselect();

        sceneMgr->setHighlight(object->modelN);

        object->pivotN->          addChild(object->pivotGeoN);
        object->manipulatorRootN->addChild(object->manipulatorN);

        {
            OSG::Node* t(0);

            switch(manipulatorMgr->getCurrentType())
            {
            case OSG::ManipulatorManager::TRANSLATE:
                t = object->xformTranslationN;
                break;

            case OSG::ManipulatorManager::ROTATE:
                t = object->xformRotationN;
                break;

            case OSG::ManipulatorManager::SCALE:
                t = object->xformScaleN;
                break;
            }

            assert(0 != t);

            manipulatorMgr->setTarget(t);
        }

        selected = true;
    }

    void
    display()
    {
        sceneMgr->redraw();
    }

    void
    reshape(int w, int h)
    {
        sceneMgr->resize(w, h);

        glutPostRedisplay();
    }

    void
    idle()
    {
        sceneMgr->idle();

        glutPostRedisplay();
    }

    void
    mouse(int button, int state, int x, int y)
    {
        switch (state)
        {
        case GLUT_DOWN:
        {
            OSG::IntersectAction* ia(OSG::IntersectAction::create());

            {
                ia->setLine(sceneMgr->calcViewRay(x, y));
                ia->apply(sceneMgr->getRoot());
            }

            bool const result(ia->didHit());

            std::string action("no action");

            if (result)
            {
                OSG::NodeRefPtr node_hit(ia->getHitObject());
                OSG::NodeRefPtr node(find_path(/* from */ node_hit, /* to */ object->intersectN));

                if (0 != node)
                {
                    if (!selected)
                    {
                        select();
                        set_pivot(ia->getHitPoint(), ia->getHitNormal());

                        action = "select";
                    }
                    else
                    {
                        if (manipulatorMgr->activate(node_hit))
                        {
                            manipulatorMgr->mouseButtonPress(button, x, y);

                            action = "manipulate";
                        }
                        else
                        {
                            set_pivot(ia->getHitPoint(), ia->getHitNormal());

                            action = "re-select";
                        }
                    }
                }
                else
                {
                    sceneMgr->mouseButtonPress(button, x, y);

                    action = "non-object picked";
                }
            }
            else
            {
                deselect();
                sceneMgr->mouseButtonPress(button, x, y);

                action = "deselect";
            }

            delete ia;

            {
                std::cout << "mouse: btn:down, " << action << std::endl;
            }
        }
        break;

        case GLUT_UP:
        {
            if (manipulatorMgr->isActive())
            {
                manipulatorMgr->mouseButtonRelease(button, x, y);
            }
            else
            {
                sceneMgr->mouseButtonRelease(button, x, y);
            }

            std::cout << "mouse: btn:up " << std::endl;
        }
        break;
        }

        glutPostRedisplay();
    }

    void
    motion(int x, int y)
    {
        if (manipulatorMgr->isActive())
        {
            manipulatorMgr->mouseMove(x, y);
        }
        else
        {
            sceneMgr->mouseMove(x, y);
        }

        glutPostRedisplay();
    }

    void
    keyboard(unsigned char key, int x, int y)
    {
        bool update_display(false);
        bool update_manipulator(false);

        switch (key) {
        case 27:
        case 'Q':
        case 'q':
        {
            window = 0;

            delete manipulatorMgr;
            delete sceneMgr;
            delete object;

            sceneRootN = 0;

            {
                OSG::commitChanges();
                OSG::Thread::getCurrentChangeList()->dumpListSizes();
            }

            OSG::osgExit();

            std::exit(EXIT_SUCCESS);
        }
        break;

        case 'C':
        case 'c':
        {
            object->toggle_change_functors();
        }
        break;

        case 'D':
        case 'd':
        {
            dump_scene(selected ? object->rootN.get() : sceneMgr->getRoot());
        }
        break;

        case 'I':
        case 'i':
        {
            sceneMgr->setStatistics(!sceneMgr->getStatistics());
            glutIdleFunc(sceneMgr->getStatistics() ? idle : 0);
        }
        break;

        case 'R':
        case 'r':
        {
            manipulatorMgr->changeManipulator(OSG::ManipulatorManager::ROTATE);
            manipulatorMgr->setTarget(object->xformRotationN);
            update_manipulator = true;
            update_display     = true;
        }
        break;

        case 'S':
        case 's':
        {
            manipulatorMgr->changeManipulator(OSG::ManipulatorManager::SCALE);
            manipulatorMgr->setTarget(object->xformScaleN);
            update_manipulator = true;
            update_display     = true;
        }
        break;

        case 'T':
        case 't':
        {
            manipulatorMgr->changeManipulator(OSG::ManipulatorManager::TRANSLATE);
            manipulatorMgr->setTarget(object->xformTranslationN);
            update_manipulator = true;
            update_display     = true;
        }
        break;

        case 'U':
        case 'u':
        {
            uniform_scale      = !uniform_scale;
            update_manipulator = true;
        }
        break;

        default:
            break;
        }

        if (update_manipulator)
        {
            OSG::ScaleManipulator* sm
                (dynamic_cast<OSG::ScaleManipulator*>(object->manipulatorN->getCore()));

            if (sm)
                sm->setUniform(uniform_scale);
        }

        if (update_display)
            glutPostRedisplay();
    }

    void
    setupGlut(int* argc, char* argv[])
    {
        glutInit(argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

        int window_id(glutCreateWindow("Manipulator Demo"));

        glutDisplayFunc (display);
        glutReshapeFunc (reshape);
        glutMouseFunc   (mouse);
        glutMotionFunc  (motion);
        glutKeyboardFunc(keyboard);

        window = OSG::GLUTWindow::create();

        window->setGlutId(window_id);
        window->init();
    }

    void
    setupScene()
    {
        manipulatorMgr = new OSG::ManipulatorManager;

        object = new object_type(manipulatorMgr->createManipulator(OSG::ManipulatorManager::TRANSLATE));

        sceneMgr = new OSG::SimpleSceneManager;

        { // sceneRootN -> object->rootN
            sceneRootN = OSG::Node::create();

            sceneRootN->setCore(OSG::Group::create());

            {
                OSG::NodeRefPtr tmp(OSG::makeCoordAxis(1.f, 2.f, false));

                OSG::setName(tmp, "scene-coordinate-axes");

                sceneRootN->addChild(tmp);
            }

            sceneRootN->addChild(object->rootN);

            OSG::setName(sceneRootN, "scene-root");
        }

        sceneMgr->setWindow     (window);
        sceneMgr->setRoot       (sceneRootN);
        sceneMgr->setClickCenter(false);
        sceneMgr->showAll       ();

        manipulatorMgr->setViewport(sceneMgr->getWindow()->getPort(0));
    }

} // namespace {

int
main(int argc, char* argv[])
{
    OSG::osgInit(argc,argv);

    setupGlut(&argc, argv);
    setupScene();

    OSG::commitChanges();

    glutReshapeWindow(600, 600);
    glutMainLoop();

    return EXIT_SUCCESS;
}
